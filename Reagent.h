#ifndef REAGENT_H
#define REAGENT_H

#include <liburing.h>

struct io_uring Ring;

void InitIU(int QUEUE_DEPTH) {

    if (io_uring_queue_init(QUEUE_DEPTH, &Ring, 0) < 0) {
        perror("Your kernel does not have io_uring support!");
    }

};

void CloseIU() {
    io_uring_queue_exit(&Ring);
}

void Write(int sock, void *Buff, size_t Buffsize) {

    struct io_uring_sqe *sqe = io_uring_get_sqe(&Ring);
    struct io_uring_cqe *cqe;

    io_uring_prep_write(sqe, sock, Buff, Buffsize, 0);
    io_uring_submit(&Ring);

    io_uring_wait_cqe(&Ring, &cqe);
    if (cqe->res < 0) {
        perror("Writing failed");
    }

    io_uring_cqe_seen(&Ring, cqe);

}

void Read(int sock, void *Buff, size_t Buffsize) {
    
    struct io_uring_sqe *sqe = io_uring_get_sqe(&Ring);
    struct io_uring_cqe *cqe;

    io_uring_prep_read(sqe, sock, Buff, Buffsize, 0);
    io_uring_submit(&Ring);

    io_uring_wait_cqe(&Ring, &cqe);
    if (cqe->res < 0) {
        perror("Reading failed");
    }
    
    io_uring_cqe_seen(&Ring, cqe);

}

#endif